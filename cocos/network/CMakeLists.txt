if(WINDOWS)
  set(PLATFORM_LINK websockets)
elseif(LINUX)
  set(PLATFORM_LINK websockets ssl crypto)
endif()

set(COCOS_NETWORK_SRC network/HttpClient.cpp network/SocketIO.cpp network/WebSocket.cpp)

if(MSVC)
  set(COCOS_NETWORK_LINK libcurl_imp ${PLATFORM_LINK})
else()
  set(COCOS_NETWORK_LINK curl ${PLATFORM_LINK} )
endif()
