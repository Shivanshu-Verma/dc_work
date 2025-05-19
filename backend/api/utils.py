def convert_cfg_to_dot(cfg_lines):
    dot_lines = [
        "digraph CFG {",
        "    rankdir=TB;",
        "    node [shape=box, style=filled, fillcolor=lightgrey];"
    ]

    for line in cfg_lines:
        if '-->' in line:
            src, dst = [part.strip() for part in line.split('-->')]
            dot_lines.append(f'    "{src}" -> "{dst}";')

    dot_lines.append("}")
    return '\n'.join(dot_lines)
