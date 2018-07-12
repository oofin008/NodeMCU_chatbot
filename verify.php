<?php
$access_token = 'qIaDaC5ms4N0NOUslPYnDU6KAWHQJCXd+njoPxivYVT92VamT85Iy9GwqYdso/CQuzQufKsTKb6j52lMXSZXt7sp195RJGz7zCvDCDRiPdGxZLefM+XA89wfRwb8eevf0WxoVJqGsDIwUQ0P5za7TAdB04t89/1O/w1cDnyilFU=';

$url = 'https://api.line.me/v1/oauth/verify';

$headers = array('Authorization: Bearer ' . $access_token);

$ch = curl_init($url);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);
$result = curl_exec($ch);
curl_close($ch);

echo $result;
