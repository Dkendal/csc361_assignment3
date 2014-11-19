# RDP header field Possible value Meaning
# Magic                                     :  magic UVicCSc361 CSc361 RDP protocol
# Type                                      : 
# type DAT Data packet
# ACK Acknowledgment packet
# SYN Synchronization packet
# FIN Finish packet
# RST Reset packet
# Sequence                                  :  seqno e.g., 0 byte sequence number
# Acknowledgment                            :  ackno e.g., 900 byte acknowledgment number
# Payload                                   :  length e.g., 900 RDP payload length in bytes
# Window                                    :  size e.g., 10240 RDP window size in bytes
# (an empty line) the end of the RDP header

require "digest/md5"

class Packet
  attr_accessor :ack,
    :dat,
    :syn,
    :fin,
    :rst,
    :seqno,
    :ackno,
    :reported_checksum,
    :reported_size,
    :content

  def magic
    "UVicCSc361"
  end

  def checksum
    content ? ::Digest::MD5.hexdigest( self.content ) : 0
  end

  def valid?
    valid_checksum? && valid_size?
  end

  ["syn", "ack", "rst", "fin", "dat"].each do |attr|

  end

  ["checksum", "size"].each do |attr|
    define_method "valid_#{attr}?" do
      attr_val = send attr
      attr_reported_val = send "reported_#{attr}"
      attr_val == attr_reported_val
    end
  end

  def reported_size
    @reported_size.to_i if @reported_size
  end

  def size
    content ? self.content.bytesize : 0
  end

  def initialize args
    self.ack = self.dat = self.syn = self.fin = self.rst = "0"
    self.ackno = self.seqno = 0

    args.each_pair do |key, val|
      self.send "#{key}=", val
    end
  end

  def self.parse str
    _, dat, syn, ack, fin, rst, seqno, ackno, size, checksum = str.split

    content = str [ str.index("\n") + 1 .. -1]

    packet = self.new({
      syn: syn,
      ack: ack,
      dat: dat,
      fin: fin,
      rst: rst,
      seqno: seqno,
      ackno: ackno,
      content: content,
      reported_size: size,
      reported_checksum: checksum
    })

    packet
  end

  def to_str
    str = [ magic, dat, syn, ack, fin, rst, seqno, ackno, size, checksum ].join " "
    str << "\n"
    str << content if content
    str
  end
end
