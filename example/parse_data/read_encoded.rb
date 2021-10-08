require "base64"

expected = "testkjadlskjflkasjfwe08u185u12w3oqew,dmf.smxa"

path = "./example/parse_data/cpp_data.bin"

encoded = (File.open path).read

decoded = Base64.decode64 encoded

if expected == decoded
  puts "Succes"
else
  puts "Failure"
end


  
