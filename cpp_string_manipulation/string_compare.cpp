bool strCompare (const char * str1, const char * str2)
{
        int i = 0;
    for (i = 0; str1[i] != '\0' || str2[i] != '\0'; ++i) {

        if (str1[i] != str2[i]) {

            return false;
        }
    }
    if (str1[i] != '\0' || str2[i] != '\0') {

        return false;
    }
    return true;
}
