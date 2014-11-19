require "client"

describe "Client" do
  describe :recv do
    let(:synpacket) do
      Packet.new syn: 1, seqno: 100
    end
    let(:socket) { double }
    subject { recv socket }

    before do
      expect(socket).to receive(:recvfrom) do
        [synpacket.to_str]
      end
    end

    it do
      subject
    end
  end
end
