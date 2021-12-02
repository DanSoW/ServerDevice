import mosca from "mosca";
import dotenv from "dotenv";
dotenv.config();

const MqttServer = new mosca.Server({
  port: 1883
});

MqttServer.on("clientConnected", function(client) {
  // Обратный вызов при наличии клиентского соединения.
  console.log("client connected", client.id);
  //console.log(client);
});
/**
   * Мониторинг сообщений темы MQTT
   * Когда у клиента есть соединение для публикации тематического сообщения
 **/
MqttServer.on("published", function(packet, client) {
  let topic = packet.topic;
  switch (topic) {
    case "temperature":
      console.log(packet.payload.toString());
      MqttServer.publish({ topic: 'temperature_result', payload: 'This is message' });
      break;
    case "other":
      console.log("message-123", packet.payload.toString());
      break;
  }
});

MqttServer.on("ready", function() {
  // Обратный вызов при запуске службы
  console.log("mqtt is running...");
});