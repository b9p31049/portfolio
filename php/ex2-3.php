<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>キーワードの受信</title>
</head>
<body>
    <h1>キーワードを受信</h1>
<?php
echo("<p>HTMLから受信したキーワードは{$_POST["p01"]}です
</p>");
echo("<p>HTMLから受信したキーワードは{$_POST["p02"]}です
</p>");
echo("<p>HTMLから受信した電話番号は{$_POST["p03"]}です
</p>");
echo("<p>HTMLから受信したURLは{$_POST["p04"]}です
</p>");
echo("<p>HTMLから受信したメールアドレスは{$_POST["p05"]}です
</p>");
echo("<p>HTMLから受信したパスワードは{$_POST["p06"]}です
</p>");
echo("<p>HTMLから受信したUTCは{$_POST["p07"]}です
</p>");
echo("<p>HTMLから受信した日付は{$_POST["p08"]}です
</p>");
echo("<p>HTMLから受信した月は{$_POST["p09"]}です
</p>");
echo("<p>HTMLから受信した週は{$_POST["p10"]}です
</p>");
?>
</body>
</html>