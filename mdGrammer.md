#Elements

*italic*   **bold**

Single return
equals space.

More returns crate segments.

Two extra spaces at the end of line __
creat a new line.

---

#Codes
Four spaces or a Tab at the begining indicate a code line.

C++:

	const int HHMDimension = 5;
	Gnuplot plotter;
	ofstream fout;
	typedef boost::array< double, HHMDimension > state_type;

Python:

	x = arange(0, 4*pi, 0.01)
	y = sin(x)
	figure(figsize=(8,4))
	plot(x, y)
	ax = gca()
	show()

LaTex:

	\begin{abstract}
	...
	\\[5pt]PACS number(s): 89.75.-k, 87.23.Ge.
	\\[5pt]{\bf Keywords:} Agent-based modeling, ...
	\end{abstract}

#References

	A [link](https://www.google.com "title") is like this. The title is optional.

	The link can also be written in this way: [G][google].

	The link can be defined somewhere else in then doc:

	[google]: http://example.com/  "google"

	![text](./path/to/img.jpg "title")

	![some other text][imgID]

	[imgID]: /url/to/img.jpg "title"

> Let us QUOTE something here.

#Lists

-   Canonical
    - Ubuntu
-   Google
    1.  Android
        - chrome
        - auto...
    1.  Go lang
        - Material design?
    1. Gmail
-   GE

# Sections

## Subsections

### Subsubsections

...

###### Header 6

use pandoc to convert .md to slides or normal article:

    pandoc mdGrammer.md -o mdGrammer.pdf

    pandoc mdGrammer.md -o mdGrammer.pdf -t beamer

    pandoc mdGrammer.md -o mdGrammer.html

    pandoc mdGrammer.md -o mdGrammer.html -t dzslides -s

    pandoc -f markdown+lhs mdGrammer.md -o slides.html -t dzslides -s -S --toc 
    
    pandoc -f markdown+lhs slides.md -o slides.html -t dzslides -i -s -S --toc --mathjax
