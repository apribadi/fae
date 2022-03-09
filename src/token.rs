pub enum Tag {
    Identifier,
}

pub struct Token {
    pub start: *const u8,
    pub stop: *const u8,
}

pub fn go() {
    println!("Hello, world!");
}
