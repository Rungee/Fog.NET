#pragma once
template<class Char_>
class NativeConstString
{
   // this is how you use it.
   public:
       NativeConstString(System::String^ s);
       ~NativeConstString() { System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr(p_)); }
       operator const Char_* () { return p_; }
   
  // no copy or assignment
  private:
      NativeConstString(const NativeConstString&);
      NativeConstString& operator = (const NativeConstString&);
  
  private:
      Char_* p_;
};
