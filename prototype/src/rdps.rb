#!/usr/bin/env ruby
# encoding: utf-8

require "socket"

sender_ip, sender_port, receiver_ip, receiver_port, sender_file_name = *ARGV

sock = UDPSocket.new
sock.bind(sender_ip, sender_port.to_i)

file = open(sender_file_name, "r")

sock.send(file.read, 0, receiver_ip, receiver_port.to_i)
