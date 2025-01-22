#include <gtest/gtest.h>



TEST(TreeTest, Parent_MS) {
  my_containers::Tree<char, std::string> tree_ch_st{
      std::pair<char, std::string>{'5', "Jazz"},
      {'\n', "I"},
      {'y', "played"},
      {'(', "with"},
      {'`', "Blues"},
      {'-', "brothers"},
      {'=', "like"},
      {'b', "Yoda"},
      {'d', "Wow"},
      {'c', "!"}};
  EXPECT_EQ(tree_ch_st.size(), 10);
  EXPECT_THROW(tree_ch_st.getParentData('5'), std::out_of_range);
  EXPECT_EQ(tree_ch_st.getParentData('y'), 'd');
  EXPECT_EQ(tree_ch_st.getParentData('`'), 'b');
  EXPECT_EQ(tree_ch_st.getParentData('\n'), '(');
  // tree_ch_st.crazyPrinter();
}


// int main(int argc, char** argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }