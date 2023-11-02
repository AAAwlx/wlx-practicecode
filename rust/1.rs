
fn main() {
    let mut s1 = String::new();

    // 创建可变引用
    let s = &mut s1;

    // 添加句子到 String 中
    let sentence = "This is a sentence.";
    s.push_str(sentence);

    // 也可以使用 push 方法来添加字符
    s.push(' '); // 添加一个空格
    s.push_str("It continues.");

    // 打印结果
    println!("{}", s);
    s.push_str("It continues.");
    

    println!("The length of '{}' .", s1);
    
        let mut s = String::from("hello");
    
        let r1 = &mut s;
        println!("{}", r1);
        let r2 = &mut s;
        println!("{}", r2);
}

fn calculate_length(s: &String) -> usize {
    s.len()
}
