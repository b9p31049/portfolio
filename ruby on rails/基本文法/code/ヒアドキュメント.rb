# 1, 式が計算されて表示
string = <<EOS
    長い
    文章
    が
    続きます
    #{1 + 1}
EOS
puts string

# 2,そのまま表示
string = <<'EOS'
    長い
    文章
    が
    続きます
    #{1 + 1}
EOS
puts string

# 3,　行の先頭に書かなくて済む
    string = <<-"EOS"
        長い
        文章
        が
        続きます
        #{1 + 1}
    EOS
    puts string