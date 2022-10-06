use std::cmp::Ordering::Equal;

pub struct Cave {
    pub label: String,
    pub is_large: bool,
    pub paths: Vec<String>,    
}

impl Cave {
    pub fn new(label: String) -> Cave {
        let upper = label.cmp(&label.to_uppercase()) == Equal;
        return Cave { label, is_large: upper, paths: vec![] };
    }
}
