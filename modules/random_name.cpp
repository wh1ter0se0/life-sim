std::string random_name(){
  std::vector<std::string> names_list = generate_vector
  ("dataset/names/male_first_names.txt");
  srand (time(NULL));
  return names_list[rand()% names_list.size()];
}
