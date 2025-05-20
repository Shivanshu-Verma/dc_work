def convert_cfg_to_dot(cfg_lines):
    dot_lines = [
        "digraph CFG {",
        "    rankdir=TB;",
        "    node [style=filled, fillcolor=lightgrey];"
        "    START [shape=Mdiamond];"
        "    END [shape=Msquare];"
    ]

    for line in cfg_lines:
        if '-->' in line:
            src, dst = [part.strip() for part in line.split('-->')]
            dot_lines.append(f'    "{src}" -> "{dst}";')

    dot_lines.append("}")
    return '\n'.join(dot_lines)
