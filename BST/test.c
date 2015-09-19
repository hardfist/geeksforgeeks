void recur(r)
{
  // static code block
  static int indent = 0;
  initialize code;
  //
  if(r)
  {
    recur(r->left);
    recur(r->right);
  }
}
