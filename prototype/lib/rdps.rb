#!/usr/bin/env ruby
# encoding: utf-8

require "socket"

class RDPPacket
  #Magic: magic UVicCSc361 CSc361 RDP protocol
  #Type: type DAT Data packet
  #ACK Acknowledgment packet
  #SYN Synchronization packet
  #FIN Finish packet
  #RST Reset packet
  #Sequence: seqno e.g., 0 byte sequence number
  #Acknowledgment: ackno e.g., 900 byte acknowledgment number
  #Payload: length e.g., 900 RDP payload length in bytes
  #Window: size e.g., 10240 RDP window size in bytes
  #(an empty line) the end of the RDP header

  def initialize type, seqno, ackno, size = 0
    @payload = ""
    @magic = "UVicCSc361"
    @type        = type
    @seqno       = seqno
    @ackno       = ackno
    @size = window_size
  end

  def payload= val
    @payload = val
    @size = val.bytesize
  end

  def read file
    self.payload = file.read avail
  end

  def avail
    1024 - to_s.bytesize - 4
  end

  def to_s
    "#{@magic} #{@type} #{@seqno.to_s} #{@ackno.to_s} #{@window_size.to_s} #{@size.to_s}\n#{@payload}\n"
  end
end

def main
  sender_ip, sender_port, receiver_ip, receiver_port, sender_file_name = *ARGV

  sock = UDPSocket.new
  sock.bind(sender_ip, sender_port.to_i)

  file = open(sender_file_name, "r")

  seqno = rand 1000

  packet = RDPPacket.new "SYN", seqno, ""

  sock.send(packet.to_s, 0, receiver_ip, receiver_port.to_i)

  #send_dat(seqno, file, receiver_ip, receiver_port, sock, packet)
end

def send_dat(seqno, file, receiver_ip, receiver_port, sock, packet)
  while !file.eof?
    packet = RDPPacket.new "DAT", seqno, 900
    seqno += 1
    packet.read file
    sock.send(packet.to_s, 0, receiver_ip, receiver_port.to_i)
  end
end

main
