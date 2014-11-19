require "packet"
require "rspec/its"

describe Packet do
  describe "creating a new packet" do
    context "with a string" do
      let(:received_message) {
        "UVicCSc361 0 1 0 0 0 100 1 3 2eeecd72c567401e6988624b179d0b14\nsup"
      }

      subject { Packet.parse received_message }

      its(:syn) { should eq "1" }
      its(:ack) { should eq "0" }
      its(:dat) { should eq "0" }
      its(:rst) { should eq "0" }
      its(:fin) { should eq "0" }
      its(:size) { should eq 3 }
      it { is_expected.to be_valid_size }
      it { is_expected.to be_valid_checksum }
      it { is_expected.to be_valid }
    end
  end

  describe "to_str" do
    let(:packet) { Packet.new dat: 1, seqno: 100, ackno: 1, content: "sup" }
    subject { packet.to_str }
    it { is_expected.to eq "UVicCSc361 1 0 0 0 0 100 1 3 2eeecd72c567401e6988624b179d0b14\nsup" }
  end
end
