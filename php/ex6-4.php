<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>クラス</title>
</head>
<body>
<h1>クラス</h1>

<table border="1">
    <?php
    class Jikanwari{
        var $name;
        var $kyoin;
        var $jikan;
        var $youbi;

        function __construct($name, $kyoin, $jikan, $youbi){
            $this ->name = $name;
            $this -> kyoin = $kyoin;
            $this -> jikan = $jikan;
            $this -> youbi = $youbi;
        }

        function createJikanwari() {
            echo("<tr>");
            echo ("<td>");
            echo (var_dump(name));
        }
    }
    ?>

</table>

</body>
</html>