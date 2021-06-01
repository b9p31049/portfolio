# 擬似変数（True, false, nilなど）

# 論理演算子（AND , OR , NOT）

    #AND(falseがでた時点で判定されない)
    # &&
    puts"#{true if true && true}"

    #OR(trueがでた時点で判定しない)
    # ||    
    puts"#{true if false || true}"

# 特殊の書き方（変数の中に値が入っていなければ代入される）
var = nil
var ||= 'value'

    #NOTの書き方(!をつけることで反転する)
    puts "#{!true ? '真' : '偽'}"
    puts "#{!false ? '真' : '偽'}" 

