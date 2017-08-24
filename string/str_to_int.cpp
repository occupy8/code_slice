enum convert_state{
    INVALID = 0,
    VALID = 1
}

struct convert_result{
    convert_state state;
    int number;
}

convert_result str_to_int(char *arr, int len){
    convert_result result;
    result.state = INVALID;
    result.number = 0;

    if(NULL == arr || 0 == len){
        return result;    
    }

    bool minus = false;
    int index = 0;
    if(arr[0] == '-'){
        minus = true;
        index++;
    }else if(arr[0] == '+'){
        index++;
    }

    long number = 0;
    while((index < len) && (arr[index] >= '0') && (arr[index] <= '9')){
        number = number*10 + (arr[index] - '0');
        //检查越界
        if((minus && number < int.MinValue) ||
                (!minus && number > int.MaxValue))
        {
            number = 0;
            result.state = INVALID;
            break;
        } 

        index++;
    }

    if(minus)
        number = -number;
    result.number = number;

    return result;
}
