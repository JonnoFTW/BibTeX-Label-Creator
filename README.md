BibTeX Label Generator for Endnote
==================================
This is a simple plugin for Endnote that generates 
BibTeX labels for Endnote to be exported using the built in BibTeX export plugin.

Some notes:

1. The format for labels is {author_surname.lower}{shortyear}, the detection of surnames may be not bullet proof.
2. It will not overwrite existing labels, if it encounters a potential duplicate label, it
will append a random 5 character string to the label, eg. if `ranu09` is used, the next time 
it sees a label that would be `ranu09`, it will use `ranu09-adf4v` instead.

Installation
------------
Copy the file from `vc9/Release/BibTex/BibTeX-Label-Creator.dll` into `My Documents/Endnote/Plugins` (create the folder if it doesn't exist) and start Endnote.

Usage
-----
Once installed:

1. Go to *Tools*->*Generate BibTeX Labels*
2. Wait for it to run, (you may need to set Endnote to display labels in the main view by right clicking the column heading and select `Label`)
3. Set Endnote to export using the BibTeX output style (*Edit*->*Output Styles*->*Open Style Manager* and make sure `BibTeX Export` is ticked),
4. Export your Endnote library to .bib (*File*->*Export*, uncheck `Export Selected References` if you want to export all your references), select the `BibTeX Export` output style, choose a file name with .bib extension and click save,
5. Use the resulting .bib file in your LaTeX documents!