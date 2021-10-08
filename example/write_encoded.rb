require "base64"

data = "testkjadlskjflkasjfwe08u185u12w3oqew,dmf.smxa"
path = "./example/ruby_data.bin"

encoded = Base64.encode64 data

puts encoded 
open(path, "wb") do |file|
  file << encoded
end

