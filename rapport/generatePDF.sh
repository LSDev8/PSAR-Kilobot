#!/bin/bash

pdflatex -interaction=nonstopmode rapport.tex
bibtex rapport
pdflatex -interaction=nonstopmode rapport.tex
pdflatex -interaction=nonstopmode rapport.tex
pdflatex -interaction=nonstopmode rapport.tex
make clean
evince rapport.pdf
