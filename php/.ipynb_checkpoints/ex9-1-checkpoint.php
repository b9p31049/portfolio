<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>データベース</title>
</head>
<body>
    <h1>データベース</h1>
<?php

$dsn = "mysql:dbname=sample01;host=localhost";

$my = new PDO($dsn, "wp", "wp");

$sql = "SELECT * FROM 授業;";
$arr = $my->query($sql);

foreach($arr as $row){
    echo("<p> {$row["授業"]} / {$row["教員"]} / {$row["曜日"]} / {$row["時間"]}</p>");
}

?>
</body>
</html>