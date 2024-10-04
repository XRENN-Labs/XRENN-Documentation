<?php
function obtainToken($username, $password) {
    $url = 'https://xrenn.ai/api/v1/auth_xrenn_token/obtain/';
    $data = array('username' => $username, 'password' => $password);

    $options = array(
        'http' => array(
            'header'  => "Content-Type: application/x-www-form-urlencoded\r\n",
            'method'  => 'POST',
            'content' => http_build_query($data),
        ),
    );
    $context  = stream_context_create($options);
    $result = file_get_contents($url, false, $context);
    if ($result === FALSE) {
        return null;
    }

    return json_decode($result, true);
}

function refreshToken($refresh) {
    $url = 'https://xrenn.ai/api/v1/auth_xrenn_token/refresh/';
    $data = array('refresh' => $refresh);

    $options = array(
        'http' => array(
            'header'  => "Content-Type: application/x-www-form-urlencoded\r\n",
            'method'  => 'POST',
            'content' => http_build_query($data),
        ),
    );
    $context  = stream_context_create($options);
    $result = file_get_contents($url, false, $context);
    if ($result === FALSE) {
        return null;
    }

    return json_decode($result, true);
}
?>