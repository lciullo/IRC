<h1 align="center">💻IRC</h1>
<p align="center">
  <img src="https://img.shields.io/badge/C++-Solutions-blue.svg?style=flat&logo=c++" alt="C++"/>
  <img src="https://img.shields.io/badge/42-000000?style=for-the-badge&logo=42&logoColor=white" alt="42"/>
</p>


A lightweight Internet Relay Chat (IRC) server implementation in C++, developed as part of the 42 curriculum.

## 📋 Overview

ft_irc is an IRC server implementation that enables real-time communication between multiple clients. This project focuses on understanding network programming, socket communication, and implementing the IRC protocol specifications.

## ✨ Features

### Server Capabilities
* User authentication and registration
* Channel creation and management
* Private messaging between users
* Channel operator privileges
* Client connection handling

### Command Support
* `/nick`: Set or change nickname
* `/join`: Join a channel
* `/privmsg`: Send private messages
* `/quit`: Disconnect from server
* `/part`: Leave a channel
* `/topic`: Set/view channel topic
* `/mode`: Set channel/user modes
* `/kick`: Remove user from channel
* `/invite`: Invite user to channel

### Network Features
* TCP/IP socket communication
* Multiple client connections
* Real-time message broadcasting
* Error handling and recovery
* Protocol compliance

## 🚀 Getting Started

### Prerequisites
* C++ compiler (C++98 standard)
* Make
* POSIX-compliant operating system

### Installation

```bash
# Clone the repository
git clone https://github.com/yourusername/ft_irc.git
cd ft_irc

# Compile the project
make
```

### Usage

```bash
# Start the server
./ircserv <port> <password>

# Connect using a client (e.g., netcat)
nc localhost <port>
```

## 🎯 Project Objectives
* Implement the IRC protocol according to specifications
* Handle multiple client connections simultaneously
* Manage channels and user permissions
* Process IRC commands and responses
* Ensure secure user authentication
* Implement proper error handling
* Handle network communication effectively

## 🏗️ Project Structure

```
ft_irc/
├── src/
│   ├── main.cpp
│   ├── Server.cpp
│   ├── Client.cpp
│   ├── Channel.cpp
│   ├── Command.cpp
│   └── Utils.cpp
├── include/
│   ├── Server.hpp
│   ├── Client.hpp
│   ├── Channel.hpp
│   ├── Command.hpp
│   └── Utils.hpp
├── Makefile
└── README.md
```

## 🤝 Contributors
- **Lisa Ciullo** - [@lciullo](https://github.com/lciullo)
- **Clémence Llovio** - [@clemllovio](https://github.com/clemllovio)
- **Aymeric Jakubczyk** - [@ajakubcz](https://github.com/AymericJakubczyk)

## 🧠 Learning Outcomes
This project provided valuable experience in:
* Network programming and socket communication
* Multi-client server architecture
* Protocol implementation and compliance
* Real-time data transmission
* User authentication and security
* Error handling in networked applications
* Collaborative development practices

## 🛠️ Technical Implementation
* Server class manages socket connections and client handling
* Client class handles user state and authentication
* Channel class implements room management and privileges
* Command handler processes IRC protocol messages
* Utils provide helper functions for common operations

## 📝 License
This project is part of the 42 school curriculum.

## 🌟 Acknowledgments
* IRC Protocol documentation
* 42 School
