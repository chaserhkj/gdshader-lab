# Script to generate options boilerplates from libHLSLcc code
import sys, re

current_comment = ""
for line in sys.stdin:
    if line.strip().startswith("//"):
        current_comment += " " + line.strip()[len("//"):].strip()
    if line.strip().startswith("static const unsigned int HLSLCC_"):
        m = re.match(r"^static const unsigned int (HLSLCC_[A-Z_]*) = .*", line)
        if m:
            flag = m.group(1)
            option = flag[len("HLSLCC_FLAG_"):].lower().replace("_", "-")
            current_comment = current_comment.replace('"', '\\"')
            help_text = f'"{current_comment}"' if current_comment else 'hint_undocumented_flag'
            print( f"""
                    app.add_flag_function("--{option},!--no-{option}",
                        [&](int count) {{flags = flags | {flag};}},
                        {help_text}
                    )->group("Compilation Flags");

                    """)
    
    if not line.strip().startswith("//"):
        current_comment = ""
