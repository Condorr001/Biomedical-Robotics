function[J]= Omni_Jacobian_Transpose(u)
%(E. Nu?o, I. Sarras, E. Panteley, and L. Basa?ez. Consensus in networks of nonidentical Euler-Lagrange systems with variable time-delays. 
%In 51st IEEE Conference on Decision and Control, pages 4721?4726, Maui,
%Hawaii, USA, Dec. 2012.)

%Joints Position (q)
    q1=u(1);
    q2=u(2);
    q3=u(3);

%Links lenght (l1,l2)

    l1=.133;
    l2=.133;


    j11=-l1*cos(q1)*cos(q2)-l2*cos(q1)*cos(q2)*sin(q3)-l2*cos(q1)*sin(q2)*cos(q3);
    
    j12=l2*sin(q1)*sin(q2)*sin(q3)+l1*sin(q1)*sin(q2)-l2*sin(q1)*cos(q2)*cos(q3);
    
    j13=-l2*sin(q1)*cos(q2)*cos(q3)+l2*sin(q1)*sin(q2)*sin(q3);
    
    j21=0;
    
    j22=l2*sin(q2)*cos(q3)+l2*cos(q2)*sin(q3)+l1*cos(q2);
    
    j23=l2*cos(q2)*sin(q3)+l2*sin(q2)*cos(q3);
    
    j31=-l2*sin(q1)*sin(q2)*cos(q3)-l1*sin(q1)*cos(q2)-l2*sin(q1)*cos(q2)*sin(q3);
    
    j32=l2*cos(q1)*cos(q2)*cos(q3)-l2*cos(q1)*sin(q2)*sin(q3)-l1*cos(q1)*sin(q2);
    
    j33=l2*cos(q1)*cos(q2)*cos(q3)-l2*sin(q3)*cos(q1)*sin(q2);
 
%Finally the Jacobian

    J=[j11 j12 j13;j21 j22 j23;j31 j32 j33]';