#!/bin/bash

pdflatex -interaction=nonstopmode specifications.tex
bibtex specifications
pdflatex -interaction=nonstopmode specifications.tex
make clean
evince specifications.pdf
