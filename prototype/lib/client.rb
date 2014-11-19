require "packet.rb"

def sendmsg socket, content
  seqno = rand 10000

  packet = Packet.new syn: 1, seqno: seqno, ackno: 1

  socket.send packet, 0

  buffer = socket.recvfrom.first

  packet = Packet.new dat: 1
  packet.content = content

  socket.send packet, 0
end

def recv socket
  first_packet = Packet.parse socket.recvfrom.first
  packet

  seqno = rand 10000
  ackno = packet.seqno + 1

  second_packet = Packet.new syn: 1, ack: 1, seqno: seqno, ackno: ackno
end

def handle_packet packet
  if packet.syn?
end
