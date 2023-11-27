function show_message(filename,message_id)
load("output_message.mat");
file_field = getfield(output_message,filename);
main_message = "'" + file_field(message_id).text+"'";
urls = "";

if (~isempty(file_field(message_id).urls))
    for ii=1:length(file_field(message_id).urls)
        urls = urls +", " + """" + file_field(message_id).urls(ii) + """";
    end
end
start_text = "fprintf(";
end_text = ")";
%fprintf(start_text+main_message+urls+end_text);
eval(start_text+main_message+urls+end_text)
end

