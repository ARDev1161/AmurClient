protoc -I ./ --cpp_out=. amur.proto
protoc -I ./ --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` amur.proto
