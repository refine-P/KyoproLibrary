# coding: utf-8

import json
import os
import pathlib
import sys

EXTENSION = {'.hpp', '.cpp', '.snippet'}
HEADER = """/*
// Place your snippets for C++ here. Each snippet is defined under a snippet name and has a prefix, body and 
// description. The prefix is what is used to trigger the snippet and the body will be expanded and inserted. Possible variables are:
// $1, $2 for tab stops, $0 for the final cursor position, and ${1:label}, ${2:another} for placeholders. Placeholders with the 
// same ids are connected.
// Example:
"Print to console": {
	"prefix": "log",
	"body": [
		"console.log('$1');",
		"$2"
	],
	"description": "Log output to console"
}
*/"""

def generate_snippet(lib_file):
	with lib_file.open(encoding='utf-8') as f:
		body = [s.rstrip() for s in f]
	
	snippet = {}

	snippet['prefix'] = lib_file.stem
	snippet['body'] = body
	snippet['description'] = lib_file.stem

	return snippet

def main():
	snippet_file = os.getenv("CPPSNIPPET")
	if not snippet_file:
		print("Please set CPPSNIPPET.")
		sys.exit(1)
	snippet_file = pathlib.Path(snippet_file)

	lib_dir = pathlib.Path(__file__).resolve().parents[1]

	snippet_dict = {}
	for lib_file in lib_dir.glob("**/*.*"):
		if lib_file.is_file() and lib_file.suffix in EXTENSION:
			snippet = generate_snippet(lib_file)
			snippet_dict[snippet['prefix']] = snippet
	snippet_json = json.dumps(snippet_dict, ensure_ascii=False, indent=4)

	with snippet_file.open("w", encoding="utf-8") as f:
		f.write(HEADER)
		f.write("\n\n")
		f.write(snippet_json)
		f.write("\n")


if __name__ == "__main__":
	main()
