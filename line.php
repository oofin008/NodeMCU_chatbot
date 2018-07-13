 <?php
  

function send_LINE($msg){
 $access_token = 'qIaDaC5ms4N0NOUslPYnDU6KAWHQJCXd+njoPxivYVT92VamT85Iy9GwqYdso/CQuzQufKsTKb6j52lMXSZXt7sp195RJGz7zCvDCDRiPdGxZLefM+XA89wfRwb8eevf0WxoVJqGsDIwUQ0P5za7TAdB04t89/1O/w1cDnyilFU='; 

  $messages = [
        'type' => 'text',
        'text' => $msg
        //'text' => $text
      ];

      // Make a POST Request to Messaging API to reply to sender
      $url = 'https://api.line.me/v2/bot/message/push';
      $data = [
		
		//Ue77a191627f6ac91899e75d92264310c
        'to' => 'U66c89e20c9977aace23a5e519ca4eebd',
        'messages' => [$messages],
      ];
      $post = json_encode($data);
      $headers = array('Content-Type: application/json', 'Authorization: Bearer ' . $access_token);

      $ch = curl_init($url);
      curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "POST");
      curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
      curl_setopt($ch, CURLOPT_POSTFIELDS, $post);
      curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
      curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);
      $result = curl_exec($ch);
      curl_close($ch);

      echo $result . "\r\n"; 
}

?>
