std::string random_job(){
  std::vector<std::string> names_list = generate_vector
  ("dataset/jobs/jobs.txt");
  srand (time(NULL));
  return names_list[rand()% names_list.size()];
}
