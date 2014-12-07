# Simple, clean, cute online store that sells in-game items
> Made in Perl, C, Python and HTML running on Apache server

# (For Ready-to-go) Building and publishing
Clone this repo, unzip the gamestore.zip inside it, the public_html folder inside it contains all the files of the website.

# (For development-fridendly) Building and publishing

Clone this repo to your McGill CS account and setup and empty public_html folder following the instructions provided by McGill. Then in the root of the project, run

    make

This will compile the C file. Then do

    make publish

This will move all the project files to public_html in the correct structure and set the permissions. You should now be able to access the website using the regular URL for student websites.  
To clean up the binaries, use

    make clean

# Demo
[Here]

# Contribubors
Team name: 江湖
- [Jack Zhang] - Front-end, Perl
- [Shao Kun Deng] - Python, CSV Database
- [Aleksi Sapon-Cousineau] - C

### Version
0.0.1

### License
MIT

[here]: http://www.cs.mcgill.ca/~szhang74
[jack zhang]: https://github.com/JackZProduction
[shao kun deng]: https://github.com/Akvp
[Aleksi Sapon-Cousineau]: https://github.com/DDoS
