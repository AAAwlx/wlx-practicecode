use std::io;
use rand::Rng;
fn main() {
    println!("Guess the number!");

    println!("Please input your guess.");

    let mut guess = String::new();

    io::stdin()
        .read_line(&mut guess)
        .expect("Failed to read line");//用来获取函数的返回值，如果成功返回ok并将函数的返回结果传回，如果失败则返回err并将报错信息返回

    println!("You guessed: {}", guess);
}
