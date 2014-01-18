webcli
======

A yubnub-style search provider, running locally.
It starts a local http server (using libmicrohttpd) and listens for search requests of the form `/?q=<query>`.
Available commands are configured with a simple plaintext config file.

Requirements
------------

* cmake >= 2.6 (build-time dependency)
* libmicrohttpd

Usage
-----

webcli understands the following commandline options:

* -h: start the http daemon
* -e: if no command was given, it just echoes back the request
* -d: daemonize (implies -h, makes webcli fork into the background)
* -p PORT: set the port to listen on
* -c FILE: read commands configuration from FILE, default is ~/.webcli-commands

A common usage would be:
`webcli -hed -p 8080`, which starts webcli including the http listener on port 8080. If a commands wasn't given, the original query is returned.

Commands configuration
----------------------

The commands are configured using a very simple plaintext config format:
`<command> <search url>`, with one command per line.

An example for Google search:
`g http://www.google.com/search?q=%s`
Using this line, all searches of the form `g <term>` are redirected to `http://www.google.com/search?q=<term>`.

There is a list of example commands in commands.example.

Copyright & License
-------------------

Copyright (c) 2014 by Maximilian Wolter ("Prof. MAAD")

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.