static const char CONTENT_CONFIG_JS[] PROGMEM = 
  "\"use strict\";var development=\"\",baseHost=window.location.hostname,basePort=window.location.port,baseEndpoint=\"//\"+baseHost;80!==basePort&&(baseEndpoint+=\":\"+basePort),baseEndpoint+=development;var statusupdate=!1,selected_network_ssid=\"\",lastmode=\"\",ipaddress=\"\";function scaleString(e,t,n){return(parseInt(e)/t).toFixed(n)}function addcolon(e){return(e=new String(e)).length<3?\"00:00\":(3==e.length&&(e=\"0\"+e),e.substr(0,2)+\":\"+e.substr(2,4))}function BaseViewModel(e,t,n){void 0===n&&(n={});var o=this;o.remoteUrl=t,ko.mapping.fromJS(e,n,o),o.fetching=ko.observable(!1)}function StatusViewModel(){var e=this;BaseViewModel.call(e,{mode:\"ERR\",networks:[],rssi:[],srssi:\"\",ipaddress:\"\",packets_sent:\"\",packets_success:\"\",emoncms_connected:\"\",mqtt_connected:\"\",free_heap:\"\",time:\"\",ctrl_mode:\"off\",ctrl_state:0},baseEndpoint+\"/status\"),e.isWifiClient=ko.pureComputed(function(){return\"STA\"==e.mode()||\"STA+AP\"==e.mode()}),e.isWifiAccessPoint=ko.pureComputed(function(){return\"AP\"==e.mode()||\"STA+AP\"==e.mode()}),e.fullMode=ko.pureComputed(function(){switch(e.mode()){case\"AP\":return\"Access Point (AP)\";case\"STA\":return\"Client (STA)\";case\"STA+AP\":return\"Client + Access Point (STA+AP)\"}return\"Unknown (\"+e.mode()+\")\"})}function ConfigViewModel(){BaseViewModel.call(this,{node_name:\"emonESP\",node_description:\"WiFi Emoncms Link\",node_type:\"\",ssid:\"\",pass:\"\",emoncms_server:\"data.openevse.com\",emoncms_path:\"/emoncms\",emoncms_apikey:\"\",emoncms_node:\"\",emoncms_fingerprint:\"\",mqtt_server:\"\",mqtt_port:\"\",mqtt_topic:\"\",mqtt_feed_prefix:\"\",mqtt_user:\"\",mqtt_pass:\"\",www_username:\"\",www_password:\"\",espflash:\"\",version:\"0.0.0\",timer_start1:\"\",timer_stop1:\"\",timer_start2:\"\",timer_stop2:\"\",voltage_output:\"\",time_offset:\"\"},baseEndpoint+\"/config\"),this.f_timer_start1=ko.pureComputed({read:function(){return addcolon(this.timer_start1())},write:function(e){this.timer_start1(e.replace(\":\",\"\"))},owner:this}),this.f_timer_stop1=ko.pureComputed({read:function(){return addcolon(this.timer_stop1())},write:function(e){this.timer_stop1(e.replace(\":\",\"\"))},owner:this}),this.f_timer_start2=ko.pureComputed({read:function(){return addcolon(this.timer_start2())},write:function(e){this.timer_start2(e.replace(\":\",\"\"))},owner:this}),this.f_timer_stop2=ko.pureComputed({read:function(){return addcolon(this.timer_stop2())},write:function(e){this.timer_stop2(e.replace(\":\",\"\"))},owner:this}),this.flowT=ko.pureComputed({read:function(){return.0371*this.voltage_output()+7.14},write:function(e){this.voltage_output((e-7.14)/.0371)},owner:this})}function LastValuesViewModel(){var a=this;a.remoteUrl=baseEndpoint+\"/lastvalues\",a.fetching=ko.observable(!1),a.lastValues=ko.observable(!1),a.values=ko.mapping.fromJS([]),a.entries=ko.mapping.fromJS([]);var r=\"\";a.update=function(e){void 0===e&&(e=function(){}),a.fetching(!0),$.get(a.remoteUrl,function(e){var t=[];if(\"\"!=e&&e!==r){r=e,a.entries.push({timestamp:(new Date).toISOString(),log:e});try{var n=JSON.parse(e);for(var o in n){var s=n[o],i=\"\";o.startsWith(\"CT\")&&(i=\" W\"),o.startsWith(\"P\")&&(i=\" W\"),o.startsWith(\"E\")&&(i=\" Wh\"),o.startsWith(\"V\")&&(i=\" V\"),o.startsWith(\"T\")&&(i=\" \"+String.fromCharCode(176)+\"C\"),t.push({key:o,value:s+i})}a.lastValues(!0),ko.mapping.fromJS(t,a.values)}catch(e){console.error(e),a.lastValues(!1)}}else a.lastValues(\"\"!=e)},\"text\").always(function(){a.fetching(!1),e()})}}function EmonEspViewModel(){var n=this;n.config=new ConfigViewModel,n.status=new StatusViewModel,n.last=new LastValuesViewModel,n.initialised=ko.observable(!1),n.updating=ko.observable(!1);var e=null;n.upgradeUrl=ko.observable(\"about:blank\"),n.start=function(){n.updating(!0),n.config.update(function(){n.status.update(function(){n.last.update(function(){n.initialised(!0),e=setTimeout(n.update,1e3),n.upgradeUrl(baseEndpoint+\"/update\"),n.updating(!1)})})})},n.update=function(){n.updating()||(n.updating(!0),null!==e&&(clearTimeout(e),e=null),n.status.update(function(){n.last.update(function(){e=setTimeout(n.update,1e3),n.updating(!1)})}))},n.wifiConnecting=ko.observable(!1),n.status.mode.subscribe(function(e){\"STA+AP\"!==e&&\"STA\"!==e||n.wifiConnecting(!1)}),n.saveNetworkFetching=ko.observable(!1),n.saveNetworkSuccess=ko.observable(!1),n.saveNetwork=function(){\"\"===n.config.ssid()?alert(\"Please select network\"):(n.saveNetworkFetching(!0),n.saveNetworkSuccess(!1),$.post(baseEndpoint+\"/savenetwork\",{ssid:n.config.ssid(),pass:n.config.pass()},function(e){n.saveNetworkSuccess(!0),n.wifiConnecting(!0)}).fail(function(){alert(\"Failed to save WiFi config\")}).always(function(){n.saveNetworkFetching(!1)}))},n.saveAdminFetching=ko.observable(!1),n.saveAdminSuccess=ko.observable(!1),n.saveAdmin=function(){n.saveAdminFetching(!0),n.saveAdminSuccess(!1),$.post(baseEndpoint+\"/saveadmin\",{user:n.config.www_username(),pass:n.config.www_password()},function(e){n.saveAdminSuccess(!0)}).fail(function(){alert(\"Failed to save Admin config\")}).always(function(){n.saveAdminFetching(!1)})},n.saveTimerFetching=ko.observable(!1),n.saveTimerSuccess=ko.observable(!1),n.saveTimer=function(){n.saveTimerFetching(!0),n.saveTimerSuccess(!1),$.post(baseEndpoint+\"/savetimer\",{timer_start1:n.config.timer_start1(),timer_stop1:n.config.timer_stop1(),timer_start2:n.config.timer_start2(),timer_stop2:n.config.timer_stop2(),voltage_output:n.config.voltage_output(),time_offset:n.config.time_offset()},function(e){n.saveTimerSuccess(!0),setTimeout(function(){n.saveTimerSuccess(!1)},5e3)}).fail(function(){alert(\"Failed to save Timer config\")}).always(function(){n.saveTimerFetching(!1)})},n.ctrlMode=function(e){var t=n.status.ctrl_mode();n.status.ctrl_mode(e),$.post(baseEndpoint+\"/ctrlmode?mode=\"+e,{},function(e){}).fail(function(){n.status.ctrl_mode(t),alert(\"Failed to switch \"+e)})},n.saveEmonCmsFetching=ko.observable(!1),n.saveEmonCmsSuccess=ko.observable(!1),n.saveEmonCms=function(){var e={server:n.config.emoncms_server(),path:n.config.emoncms_path(),apikey:n.config.emoncms_apikey(),node:n.config.emoncms_node(),fingerprint:n.config.emoncms_fingerprint()};\"\"===e.server||\"\"===e.node?alert(\"Please enter Emoncms server and node\"):32!=e.apikey.length?alert(\"Please enter valid Emoncms apikey\"):\"\"!==e.fingerprint&&59!=e.fingerprint.length?alert(\"Please enter valid SSL SHA-1 fingerprint\"):(n.saveEmonCmsFetching(!0),n.saveEmonCmsSuccess(!1),$.post(baseEndpoint+\"/saveemoncms\",e,function(e){n.saveEmonCmsSuccess(!0)}).fail(function(){alert(\"Failed to save Admin config\")}).always(function(){n.saveEmonCmsFetching(!1)}))},n.saveMqttFetching=ko.observable(!1),n.saveMqttSuccess=ko.observable(!1),n.saveMqtt=function(){var e={server:n.config.mqtt_server(),port:n.config.mqtt_port(),topic:n.config.mqtt_topic(),prefix:n.config.mqtt_feed_prefix(),user:n.config.mqtt_user(),pass:n.config.mqtt_pass()};\"\"===e.server?alert(\"Please enter MQTT server\"):(n.saveMqttFetching(!0),n.saveMqttSuccess(!1),$.post(baseEndpoint+\"/savemqtt\",e,function(e){n.saveMqttSuccess(!0)}).fail(function(){alert(\"Failed to save MQTT config\")}).always(function(){n.saveMqttFetching(!1)}))}}function toggle(e){var t=document.getElementById(e);\"block\"==t.style.display?t.style.display=\"none\":t.style.display=\"block\"}BaseViewModel.prototype.update=function(e){void 0===e&&(e=function(){});var t=this;t.fetching(!0),$.get(t.remoteUrl,function(e){ko.mapping.fromJS(e,t)},\"json\").always(function(){t.fetching(!1),e()})},StatusViewModel.prototype=Object.create(BaseViewModel.prototype),StatusViewModel.prototype.constructor=StatusViewModel,ConfigViewModel.prototype=Object.create(BaseViewModel.prototype),ConfigViewModel.prototype.constructor=ConfigViewModel,$(function(){var e=new EmonEspViewModel;ko.applyBindings(e),e.start()}),document.getElementById(\"apoff\").addEventListener(\"click\",function(e){var t=new XMLHttpRequest;t.open(\"POST\",\"apoff\",!0),t.onreadystatechange=function(){var e;4==t.readyState&&200==t.status&&(e=t.responseText,console.log(e),document.getElementById(\"apoff\").style.display=\"none\",\"\"!==ipaddress&&(window.location=\"http://\"+ipaddress))},t.send()}),document.getElementById(\"reset\").addEventListener(\"click\",function(e){var t;confirm(\"CAUTION: Do you really want to Factory Reset? All setting and config will be lost.\")&&((t=new XMLHttpRequest).open(\"POST\",\"reset\",!0),t.onreadystatechange=function(){var e;4==t.readyState&&200==t.status&&(e=t.responseText,console.log(e),0!==e&&(document.getElementById(\"reset\").innerHTML=\"Resetting...\"))},t.send())}),document.getElementById(\"restart\").addEventListener(\"click\",function(e){var t;confirm(\"Restart emonESP? Current config will be saved, takes approximately 10s.\")&&((t=new XMLHttpRequest).open(\"POST\",\"restart\",!0),t.onreadystatechange=function(){var e;4==t.readyState&&200==t.status&&(e=t.responseText,console.log(e),0!==e&&(document.getElementById(\"reset\").innerHTML=\"Restarting\"))},t.send())});\n"
  "//# sourceMappingURL=config.js.map\n";
