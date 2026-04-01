import json

# stops commentjson from being a dependency
def strip_comments(text):
    result = []
    i = 0
    length = len(text)

    in_single = False   # //
    in_multi  = False   # /* */
    in_string = False   # "..."

    while i < length:
        char = text[i]
        next_char = text[i + 1] if i + 1 < length else ""

        # string literals
        if not in_single and not in_multi:
            if char == '"' and (i == 0 or text[i - 1] != '\\'):
                in_string = not in_string
                result.append(char)
                i += 1
                continue

        if in_string:
            result.append(char)
            i += 1
            continue

        # start of a single-line comment
        if not in_multi and char == '/' and next_char == '/':
            in_single = True
            i += 2
            continue

        # start of a multi-line comment
        if not in_single and char == '/' and next_char == '*':
            in_multi = True
            i += 2
            continue

        # end of a single-line comment
        if in_single and char == '\n':
            in_single = False
            result.append(char)
            i += 1
            continue

        # end of a multi-line comment
        if in_multi and char == '*' and next_char == '/':
            in_multi = False
            i += 2
            continue

        # skip characters inside comments
        if in_single or in_multi:
            i += 1
            continue

        # normal character
        result.append(char)
        i += 1

    return ''.join(result)

def load_json_with_comments(path):
    with open(path, encoding="utf-8") as f:
        raw = f.read()

    cleaned = strip_comments(raw)
    return json.loads(cleaned)
