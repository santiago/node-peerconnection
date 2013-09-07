#ifndef __NODE_PEERCONNECTION_NODE_PEER_CONNECTION_CLIENT_H__
#define __NODE_PEERCONNECTION_NODE_PEER_CONNECTION_CLIENT_H__
#pragma once

#include <map>
#include <string>

#include <v8.h>
#include <node.h>

#include "peer_connection_client.h"

using namespace v8;
using namespace node;

namespace NodePeerConnection {
  class NodePeerConnectionClient : public node::ObjectWrap,
                                   public PeerConnectionClientObserver {
    public:
      Persistent<Function> Emit;
      NodePeerConnectionClient();
      virtual ~NodePeerConnectionClient();
  
      static Persistent<FunctionTemplate> constructor;
      static void Initialize(Handle<Object> target);      
      static Handle<Value> New(const Arguments &args);
      static Handle<Value> Connect(const Arguments &args);
  
      //
      // PeerConnectionClientObserver implementation.
      //
      virtual void OnSignedIn();
      virtual void OnDisconnected();
      virtual void OnPeerConnected(int id, const std::string& name);
      virtual void OnPeerDisconnected(int id);
      virtual void OnMessageFromPeer(int peer_id, const std::string& message);
      virtual void OnMessageSent(int err);
      virtual void OnServerConnectionFailure();
      
    protected:
      int peer_id_;
  };
}

#endif // __NODE_PEERCONNECTION_NODE_PEER_CONNECTION_CLIENT_H__