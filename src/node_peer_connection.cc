//
// PeerConnection.cc
//
// Copyright (c) 2012 Sofrit0 <sgaviria@gmail.com>
//
#include "node_peer_connection.h"

#include "talk/base/logging.h"
#include "talk/app/webrtc/peerconnection.h"

namespace NodePeerConnection {
  const char kAudioLabel[] = "audio_label";
  const char kVideoLabel[] = "video_label";
  const char kStreamLabel[] = "stream_label";

  Persistent <FunctionTemplate> PeerConnection::constructor;

  void PeerConnection::Initialize(Handle<Object> target) {
    HandleScope scope;

    // Constructor
    constructor = Persistent<FunctionTemplate>::New(FunctionTemplate::New(PeerConnection::New));
    constructor-> InstanceTemplate()-> SetInternalFieldCount(1);
    constructor-> SetClassName(String::NewSymbol("PeerConnection"));

    // Local<ObjectTemplate> proto = constructor->PrototypeTemplate();
    // Browser API
    NODE_SET_PROTOTYPE_METHOD(constructor, "addStream", AddStream);
    NODE_SET_PROTOTYPE_METHOD(constructor, "removeStream", RemoveStream);
    NODE_SET_PROTOTYPE_METHOD(constructor, "createOffer", CreateOffer);
    NODE_SET_PROTOTYPE_METHOD(constructor, "createAnswer", CreateAnswer);
    NODE_SET_PROTOTYPE_METHOD(constructor, "setLocalDescription", SetLocalDescription);
    NODE_SET_PROTOTYPE_METHOD(constructor, "setRemoteDescription", SetRemoteDescription);
    NODE_SET_PROTOTYPE_METHOD(constructor, "updateIce", UpdateIce);
    NODE_SET_PROTOTYPE_METHOD(constructor, "addIceCandidate", AddIceCandidate);
    // Still not in Browser API
    NODE_SET_PROTOTYPE_METHOD(constructor, "canSendDtmf", CanSendDtmf);
    NODE_SET_PROTOTYPE_METHOD(constructor, "sendDtmf", SendDtmf);
  
    // addEventListener: function addEventListener() { [native code] }
    // close: function close() { [native code] }
    // dispatchEvent: function dispatchEvent() { [native code] }
    // removeEventListener: function removeEventListener() { [native code] }
  
    /*proto->SetAccessor(String::NewSymbol("ready_state"), GetReadyState);
    proto->SetAccessor(String::NewSymbol("ice_state"), GetIceState);
    proto->SetAccessor(String::NewSymbol("local_description"), GetLocalDescription);
    proto->SetAccessor(String::NewSymbol("remote_description"), GetRemoteDescription);*/

    target-> Set(String::NewSymbol("PeerConnection"), constructor-> GetFunction());
  }

  std::string GetEnvVarOrDefault(const char* env_var_name,
                                 const char* default_value) {
    std::string value;
    const char* env_var = getenv(env_var_name);
    if (env_var)
      value = env_var;

    if (value.empty())
      value = default_value;

    return value;
  }

  std::string GetPeerConnectionString() {
    return GetEnvVarOrDefault("WEBRTC_CONNECT", "stun:stun.l.google.com:19302");
  }

  Handle<Value> PeerConnection::New(const Arguments & args) {
    HandleScope scope;
  
    if (!args[0]->IsObject()) {
      return ThrowException(Exception::TypeError(
      String::New("You must specify an object as first argument")));
    }
    
    Local<Object> obj = args[0]->ToObject();
  
    Local<Array> servers_arg = Local<Array>::Cast(obj->Get(String::NewSymbol("iceServers")));
    int argc = servers_arg->Length();

    webrtc::JsepInterface::IceServers servers;
    webrtc::JsepInterface::IceServer server;
    std::string server_uri;
    
    if (!argc > 0) {
      server_uri = GetPeerConnectionString();
    } else {
      server_uri = (const char*) *servers_arg->Get(Integer::New(0))->ToString();
    }
    
    PeerConnection *peerconnection = new PeerConnection();

    ASSERT(peerconnection->peer_connection_factory_.get() == NULL);
    ASSERT(peerconnection->peer_connection_.get() == NULL);

    peerconnection->peer_connection_factory_ = webrtc::CreatePeerConnectionFactory();

    if (!peerconnection->peer_connection_factory_.get()) {
      peerconnection->DeletePeerConnection();
      // Throw Exception ?
      return Undefined();
    }

    server.uri = server_uri;
    
    servers.push_back(server);
    
    peerconnection->peer_connection_ = peerconnection->peer_connection_factory_->CreatePeerConnection(servers, NULL, peerconnection);
    if (!peerconnection->peer_connection_.get()) {
      peerconnection->DeletePeerConnection();
    }

    // return peer_connection_.get() != NULL;
    
    peerconnection->Wrap(args.This());
    return args.This();
  }

  PeerConnection::PeerConnection() : ObjectWrap() {
  };
  
  ~PeerConnection::PeerConnection() {};

  Handle<Value> PeerConnection::AddStream(const Arguments & args) {
    /*if (active_streams_.find(kStreamLabel) != active_streams_.end())
      return;  // Already added.

    talk_base::scoped_refptr<webrtc::LocalAudioTrackInterface> audio_track(
      peer_connection_factory_->CreateLocalAudioTrack(kAudioLabel, NULL));

    talk_base::scoped_refptr<webrtc::LocalVideoTrackInterface> video_track(
      peer_connection_factory_->CreateLocalVideoTrack(
        kVideoLabel, OpenVideoCaptureDevice()));
  
    // main_wnd_->StartLocalRenderer(video_track);

    talk_base::scoped_refptr<webrtc::LocalMediaStreamInterface> stream =
      peer_connection_factory_->CreateLocalMediaStream(kStreamLabel);

    stream->AddTrack(audio_track);
    stream->AddTrack(video_track);
    if (!peer_connection_->AddStream(stream, NULL)) {
      // LOG(LS_ERROR) << "Adding stream to PeerConnection failed";
    }
  
    typedef std::pair<std::string,
            talk_base::scoped_refptr<webrtc::MediaStreamInterface> >
      MediaStreamPair;
    
    active_streams_.insert(MediaStreamPair(stream->label(), stream));*/
    
    return Undefined();
  }

  Handle<Value> PeerConnection::RemoveStream(const Arguments & args) {
    return Undefined();
  }

  Handle<Value> PeerConnection::CanSendDtmf(const Arguments & args) {
    return Undefined();
  }

  Handle<Value> PeerConnection::SendDtmf(const Arguments & args) {
    return Undefined();
  }

  Handle<Value> PeerConnection::CreateOffer(const Arguments & args) {
    return Undefined();
  }

  Handle<Value> PeerConnection::CreateAnswer(const Arguments & args) {
    return Undefined();
  }

  Handle<Value> PeerConnection::SetLocalDescription(const Arguments & args) {
    return Undefined();
  }

  Handle<Value> PeerConnection::SetRemoteDescription(const Arguments & args) {
    return Undefined();
  }

  Handle<Value> PeerConnection::UpdateIce(const Arguments & args) {
    return Undefined();
  }

  Handle<Value> PeerConnection::AddIceCandidate(const Arguments & args) {
    return Undefined();
  }

  /*Handle<Value> PeerConnection::GetReadyState(Local<String> prop, const AccessorInfo &info) {
    return Undefined();
  }

  Handle<Value> PeerConnection::GetIceState(Local<String> prop, const AccessorInfo &info) {
    return Undefined();
  }

  Handle<Value> PeerConnection::GetLocalDescription(Local<String> prop, const AccessorInfo &info) {
    return Undefined();
  }

  Handle<Value> PeerConnection::GetRemoteDescription(Local<String> prop, const AccessorInfo &info) {
    return Undefined();
  }*/

  //
  // PeerConnectionObserver implementation.
  //

  void PeerConnection::OnError() {
    LOG(LS_ERROR) << __FUNCTION__;
    // UI
    // main_wnd_->QueueUIThreadCallback(PEER_CONNECTION_ERROR, NULL);
  }

  // Called when a remote stream is added
  void PeerConnection::OnAddStream(webrtc::MediaStreamInterface* stream) {
    LOG(INFO) << __FUNCTION__ << " " << stream->label();

    stream->AddRef();
    // UI
    // main_wnd_->QueueUIThreadCallback(NEW_STREAM_ADDED, stream);
  }

  void PeerConnection::OnRemoveStream(webrtc::MediaStreamInterface* stream) {
    LOG(INFO) << __FUNCTION__ << " " << stream->label();
    stream->AddRef();
    // UI
    // main_wnd_->QueueUIThreadCallback(STREAM_REMOVED, stream);
  }

  void PeerConnection::OnIceCandidate(const webrtc::IceCandidateInterface* candidate) {
    LOG(INFO) << __FUNCTION__ << " " << candidate->sdp_mline_index();
    
    Local<Value> callback;
    callback = this->handle_->Get(NODE_PSYMBOL("onicecandidate"));
    if (!callback->IsFunction()) {
  		return;
		}
    
    Persistent<Function> callback_function = Persistent<Function>::New(Local<Function>::Cast(callback));  
		Local<Value> argv[1];
		argv[0] = Local<Value>::New(String::New("hola"));
		callback_function->Call(Context::GetCurrent()->Global(), 1, argv);
    
    /*Json::StyledWriter writer;
    Json::Value jmessage;

    jmessage[kCandidateSdpMidName] = candidate->sdp_mid();
    jmessage[kCandidateSdpMlineIndexName] = candidate->sdp_mline_index();
    std::string sdp;
    if (!candidate->ToString(&sdp)) {
      LOG(LS_ERROR) << "Failed to serialize candidate";
      return;
    }
    jmessage[kCandidateSdpName] = sdp;
    SendMessage(writer.write(jmessage));*/
  }

  void PeerConnection::DeletePeerConnection() {
    this->peer_connection_ = NULL;
    this->active_streams_.clear();
    this->peer_connection_factory_ = NULL;
    this->peer_id_ = -1;
  } 
} //namespace NodePeerConnection
