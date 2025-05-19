import os
import subprocess
import tempfile

from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status
from .utils import convert_cfg_to_dot

class ConvertView(APIView):
    """
    POST /api/convert/
    Body: multipart/form-data with key 'rtl_file' (the .v file)
    Returns JSON { "cfg": "<text of cfg.txt>" }
    """

    def post(self, request):
        rtl_file = request.FILES.get('rtl_file')
        if not rtl_file:
            return Response(
                {'error': "Missing 'rtl_file'."},
                status=status.HTTP_400_BAD_REQUEST
            )

        with tempfile.TemporaryDirectory() as tmpdir:
            # 1) Save uploaded RTL to disk
            in_path  = os.path.join(tmpdir, 'input.v')
            san_path = os.path.join(tmpdir, 'sanitized.v')
            cfg_path = os.path.join(tmpdir, 'cfg.txt')

            with open(in_path, 'wb') as f:
                for chunk in rtl_file.chunks():
                    f.write(chunk)

            # 2) Run parser (sanitizer)
            parser_bin = '/app/cpp_tools/build/parser'
            subprocess.run(
                [parser_bin, in_path, san_path],
                check=True
            )

            # 3) Prepare loop_cfg input
            #    If loop_cfg only reads 'my_output.txt', rename:
            myout = os.path.join(tmpdir, 'my_output.txt')
            os.rename(san_path, myout)

            # 4) Run loop_cfg
            loopcfg_bin = '/app/cpp_tools/build/loop_cfg'
            subprocess.run(
                [loopcfg_bin],
                cwd=tmpdir,
                check=True
            )

            # 5) Read back cfg.txt
            try:
                with open(cfg_path, 'r') as f:
                    cfg_text = f.read()
                    dot_text = convert_cfg_to_dot(cfg_text.strip().split('\n'))
            except FileNotFoundError:
                return Response(
                    {'error': 'CFG generation failed.'},
                    status=status.HTTP_500_INTERNAL_SERVER_ERROR
                )

        return Response({'cfg': cfg_text,'dot': dot_text}, status=status.HTTP_200_OK)
