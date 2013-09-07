#include <stdio.h>
#include <iostream>

// #include "PeerConnection.h"
#include "node_peer_connection_client.h"

namespace NodePeerConnection {
  void Initialize(Handle<Object> target) {
    HandleScope scope;

    NodePeerConnectionClient::Initialize(target);
    //    PeerConnection::Initialize(target);

    target->Set(v8::String::New("webrtcVersion"), v8::String::New("Unknown"));
  }
}
NODE_MODULE(webrtc, NodePeerConnection::Initialize);