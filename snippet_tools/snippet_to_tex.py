#coding: utf-8

import sys
import os
import json

def generate_snippet(dir_name, file_name):
	root_name = os.path.splitext(file_name)[0]
	full_path = os.path.abspath(os.path.join(dir_name, file_name))

	with open(full_path, encoding='utf-8') as f:
		body = f.read()
	
	snippet = r"\begin{lstlisting}" + "\n" + body + r"\end{lstlisting}" + "\n"

	return snippet


if __name__ == "__main__":

	print(r"\documentclass{jsarticle}")
	print(r"\usepackage{listings, jlisting}")

	setting = r"""\lstset{% 
	language={C++},%
	basicstyle={\small},% 
	identifierstyle={\small},% 
	ndkeywordstyle={\small},% 
	stringstyle={\small\ttfamily},% 
	frame={tb},% 
	breaklines=true,% 
	columns=[l]{fullflexible},% 
	numbers=left,% 
	xrightmargin=0zw,% 
	xleftmargin=3zw,% 
	numberstyle={\scriptsize},% 
	stepnumber=1,% 
	numbersep=1zw,% 
	morecomment=[l]{//}% 
	}"""
	print(setting)
		
	print(r"\begin{document}")
	print(r"\tableofcontents")
	print(r"\clearpage")

	dir_name = os.path.abspath(os.path.join(os.path.dirname(__file__), os.pardir))
	lib_list = os.listdir(path=dir_name)
	for file_name in lib_list:
		if file_name[-3:] not in {'hpp', 'cpp'}:
			continue
		print("\section{%s}\n" % file_name.replace("_", r"\_"))
		snippet = generate_snippet(dir_name, file_name)
		print(snippet)

	print(r"\end{document}")
