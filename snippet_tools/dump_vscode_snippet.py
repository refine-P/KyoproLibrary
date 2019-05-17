#coding: utf-8

import sys
import os
import json

def generate_snippet(dir_name, file_name):
	root_name = os.path.splitext(file_name)[0]
	full_path = os.path.abspath(os.path.join(dir_name, file_name))

	with open(full_path, encoding='utf-8') as f:
		body = [s.rstrip() for s in f]
	
	snippet = {}

	snippet['prefix'] = root_name
	snippet['body'] = body
	snippet['description'] = root_name

	return snippet


if __name__ == "__main__":

	header = """/*
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

	print(header)
	print()

	dir_name = os.path.abspath(os.path.join(os.path.dirname(__file__), os.pardir))
	snippet_dict = {}

	lib_list = os.listdir(path=dir_name)
	for file_name in lib_list:
		if file_name[-3:] not in {'hpp', 'cpp'}:
			continue
		snippet = generate_snippet(dir_name, file_name)
		snippet_dict[snippet['prefix']] = snippet

	snippet_json = json.dumps(snippet_dict, ensure_ascii=False, indent=4)
	print(snippet_json)