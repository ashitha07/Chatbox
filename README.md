# Chatboxx

Chatboxx is a chat application developed over XMPP.

## Installation

Run the Chatboxx.pro file.

## Pre-requisites

QXmpp and QT5 or above should be installed already

## Usage

On Running the Chatboxx.pro file, the Chatboxx Login page will appear.
The registered user should login and select from the list of buddies.
Once the buddy is selected, the user is prompted a chat window where he can chat with the buddy.

Note
====
The server details can be edited in server.ini file
Currently the host configured is "xmpp.is"
:

## Known issues and improvements

Issues
======
1. There is a delay for interaction with XMPP server for approx ~10 sec. Hence a delay is observed on getting connected(3-4 secs) and roster signals from the server(10-15 secs).

2. The server gets randomly disconnected during the chat and does not get re-connected. To resume chat, it needs to be logged out and logged in again.

Improvements/ enhancements
==========================
1. There can be an option for the user to update his own online presence
2. There can be an option to show notification when a chat arrives
3. The performance can be improved by introducing caching mechanisms for buddies etc.

