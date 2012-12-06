#include <stdio.h>
#include <iostream>

#include "PeerConnection.h"

namespace NodePeerConnection {
  extern "C" void
  init(Handle <Object> target) {
    HandleScope scope;
    PeerConnection::Initialize(target);

    target->Set(v8::String::New("webrtcVersion"), v8::String::New("Unknown"));
  }

  NODE_MODULE(peerconnection, init);
}