
## Network Stuff

### Basic Concepts

- Machines on the internet (or modern local networks) have IP addresses.
  - 123.123.1.32 - IPv4 addresses are written as four decimal numbers,
    with each of those ranging from 0-255. That's a 32 bit / 4 byte number.
  - In the modern (post-2005) world, there are also IPv6 addresses,
    which are 128-bit numbers written as groups of 4 hex digits.
    (e.g. 7d65::21bf:9329:bc9e:cb75)
- Computers can send IP packets to other computers on the same network
using the destination computer's IP address.
  - IP packets are stateless. There's no "connection".
  - IP packets are unreliable. They may just not get delivered.
  - Multiple IP packets have no order.
  - IP packets have a size limit. Thinking 1400B isn't entirely wrong.
  - You may send packets A, B, C, D, E and the receiving computer
  may get packets C, D, A, E
- The TCP protocol is built on top of IP, and adds:
  - A TCP port number, to distinguish multiple network services hosted
  on the same machine. (64k TCP ports)
  - Adds a concept of connections, which it uses to simulate a reliable
  bi-directional stream.
- Basic TCP protocol:
  - Send a bunch of packets (e.g. #1 - 100).
  - Recipient sends back a response saying which packets it got.
  - Resend any that got dropped and send new ones, such that there are
    always some number in flight (e.g. 100).
- IP has no concept of "client" or "server". You just send packets.
- TCP has one side listen and one side connect.
- A typical pattern is a server program that listens and a client
program that connects.
