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
2. Wait for it to run, (you may need to set Endnote to display labels in the main view)
3. Set Endnote to export using the BibTeX exporter, and use the resulting .bib file in your
LaTeX documents.
4. Enjoy!