// CC 2013 Sofrit0
// NodePeerConnectionClient is a client to the signaling server.

#include "node_peer_connection_client.h"
#include <stdio.h>

namespace NodePeerConnection {
  static PeerConnectionClient *client_ = NULL;
  static NodePeerConnectionClient *peer_ = NULL;
  static Persistent<String> emit_symbol = NODE_PSYMBOL("emit");

  Persistent <FunctionTemplate> NodePeerConnectionClient::constructor;
  
  void NodePeerConnectionClient::Initialize(Handle<Object> target) {
    HandleScope scope;
  
    // Constructor
    constructor = Persistent<FunctionTemplate>::New(
                          FunctionTemplate::New(NodePeerConnectionClient::New));
    constructor-> InstanceTemplate()-> SetInternalFieldCount(1);
    constructor-> SetClassName(String::NewSymbol("PeerConnectionClient"));
  
    NODE_SET_PROTOTYPE_METHOD(constructor, "connect", Connect);
    
    target-> Set(String::NewSymbol("PeerConnectionClient"), constructor-> GetFunction());
  }

  NodePeerConnectionClient::NodePeerConnectionClient() : ObjectWrap() {
    peer_id_ = -1;
    client_ = new PeerConnectionClient();
    client_-> RegisterObserver(this);
    
    printf("NodePeerConnectionClient");
  }

  NodePeerConnectionClient::~NodePeerConnectionClient() {
    Emit.Dispose();
    Emit.Clear();
  }
  
  Handle<Value> NodePeerConnectionClient::New(const Arguments & args) {
    HandleScope scope;

    peer_ = new NodePeerConnectionClient();

    peer_->Wrap(args.This());
    peer_->Ref();

    peer_->Emit = Persistent<Function>::New(
                    Local<Function>::Cast(peer_->handle_->Get(emit_symbol))
                  );
    
    return args.This();
  }
  
  Handle<Value> NodePeerConnectionClient::Connect(const Arguments & args) {
    HandleScope scope;
    
    // Extract server argument
    Local<Value> server_arg = args[0];
    if (!server_arg->IsString()) {
      return ThrowException(Exception::TypeError(
        String::New("Server argument must be a string")));
    }
    String::Utf8Value server(server_arg->ToString());
          
    // Extract port argument
    Local<Value> port_arg = args[1];
    if (!port_arg->IsNumber()) {
      return ThrowException(Exception::TypeError(
        String::New("Port argument must be a number")));
    }
    int port(port_arg->IntegerValue());
          
    // Extract hostname argument
    Local<Value> hostname_arg = args[2];
    if (!hostname_arg->IsString()) {
      return ThrowException(Exception::TypeError(
        String::New("Hostname argument must be a string")));
    }
    String::Utf8Value hostname(hostname_arg->ToString());
    printf("Connect!");
    client_ ->Connect(
      std::string(*server), 
      port,
      std::string(*hostname)
    );
    
    return Undefined();
  }
  
  Handle<Value> PeersMapToObject() {
    HandleScope scope;
    
    Peers peers_m = client_->peers();
    Peers::iterator it;
    Local<Object> peers = Object::New();
    for(it = peers_m.begin(); it != peers_m.end(); it++) {
      peers->Set(Integer::New(it->first), String::New(it->second.c_str()));
    }
    
    return scope.Close(peers);
  }
  
  //
  // PeerConnectionClientObserver implementation.
  //
  
  void NodePeerConnectionClient::OnSignedIn() {
//    LOG(INFO) << __FUNCTION__;
    
    Local<Object> peers = PeersMapToObject()->ToObject();
    
    Handle<Value> emit_argv[2] = {
      String::New("signed_in"),
      peers
    };

    TryCatch try_catch;

    peer_->Emit->Call(
      peer_->handle_, 2, emit_argv
    );
    
    if (try_catch.HasCaught())
      FatalException(try_catch);
  }
  
  void NodePeerConnectionClient::OnDisconnected() {
//    LOG(INFO) << __FUNCTION__;
  
    Handle<Value> emit_argv[1] = { String::New("disconnected") };

    TryCatch try_catch;
    
    peer_->Emit->Call(
      peer_->handle_, 1, emit_argv
    );
    
    if (try_catch.HasCaught())
      FatalException(try_catch);
  }
  
  void NodePeerConnectionClient::OnPeerConnected(int id, const std::string& name) {
    Local<Object> peers = PeersMapToObject()->ToObject();
    
    Handle<Value> emit_argv[2] = {
      String::New("peer_connected"),
      peers
    };

    TryCatch try_catch;

    peer_->Emit->Call(
      peer_->handle_, 2, emit_argv
    );
    
    if (try_catch.HasCaught())
      FatalException(try_catch);
  }
  
  void NodePeerConnectionClient::OnPeerDisconnected(int id) {
//    LOG(INFO) << __FUNCTION__;
    if (id == peer_id_) {
//      LOG(INFO) << "Our peer disconnected";
      // main_wnd_->QueueUIThreadCallback(PEER_CONNECTION_CLOSED, NULL);
    } else {
      Local<Object> peers = PeersMapToObject()->ToObject();
      
      Handle<Value> emit_argv[2] = {
        String::New("peer_disconnected"),
        peers
      };
  
      TryCatch try_catch;
  
      peer_->Emit->Call(
        peer_->handle_, 2, emit_argv
      );
      
      if (try_catch.HasCaught())
        FatalException(try_catch);
      
    }
  }
  
  void NodePeerConnectionClient::OnMessageFromPeer(int peer_id, const std::string& message) {
//    ASSERT(peer_id_ == peer_id || peer_id_ == -1);
//    ASSERT(!message.empty());
  
    if (peer_id != peer_id_) {
//      ASSERT(peer_id_ != -1);
//      LOG(WARNING) << "Received a message from unknown peer while already in a "
//                      "conversation with a different peer.";
      return;
    }

    Handle<Value> emit_argv[2] = {
      String::New("message_from_peer"),
      String::New(message.c_str())
    };
  
    TryCatch try_catch;

    peer_->Emit->Call(
      peer_->handle_, 2, emit_argv
    );
    
    if (try_catch.HasCaught())
      FatalException(try_catch);
  }
  
  void NodePeerConnectionClient::OnMessageSent(int err) {
    Handle<Value> emit_argv[1] = { String::New("message_sent") };
  
    TryCatch try_catch;

    peer_->Emit->Call(
      peer_->handle_, 1, emit_argv
    );
    
    if (try_catch.HasCaught())
      FatalException(try_catch);
      
    // Process the next pending message if any.
    // main_wnd_->QueueUIThreadCallback(SEND_MESSAGE_TO_PEER, NULL);
  }
  
  void NodePeerConnectionClient::OnServerConnectionFailure() {
      //main_wnd_->MessageBox("Error", ("Failed to connect to " + server_).c_str(),
      //                      true);
  }
} // namespace NodePeerConnection
