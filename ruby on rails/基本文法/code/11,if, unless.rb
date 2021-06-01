# if分は、真（True）である場合に動作


country = 'us'

if country == 'ja'
    puts '日本'
elsif country == 'us'
    puts 'アメリカ'
else
    puts 'その他の国'
end

# unless 偽(false, nil)の際に実行される

unless nil
    puts 'nilは偽'
end

unless false
    puts 'falseは偽'
end

unless 0
    puts '0は偽'
end


# 一行でも可能
country = "ja"
'日本' if country == "ja"

country = 'us'
'その他の国' unless country == 'jp'


#　三項演算子(条件演算子)

    # 真だった場合、コロンの手前
    # 偽だった場合、コロンの後ろが行われる

country = 'ja'

place = country == 'ja' ? '日本' : '海外'
puts "#{place}"

place = country == '' ? '日本' : '海外'
puts "#{place}"


# rubyでは最後の式の結果が戻り値となる

score = 60

result = if score >= 80
            '優秀'
         elsif score >= 50
            '普通'
         else 
            'やや劣る'
         end
puts result    
