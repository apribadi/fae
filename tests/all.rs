use expect_test::expect;
use fae;

#[test]
fn test_add() {
    assert!(fae::lex::add(1, 2) == 3);
}

#[test]
fn test_expect() {
    expect![[r#"3"#]].assert_eq(format!("{}", 1 + 2).as_str());
}
