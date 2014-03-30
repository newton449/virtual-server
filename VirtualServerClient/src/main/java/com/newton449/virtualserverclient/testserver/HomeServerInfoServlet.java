package com.newton449.virtualserverclient.testserver;

import com.newton449.virtualserverclient.home.client.model.ServerInfoModel;
import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * It sends a {@link ServerInfoModel}
 *
 * @author Steven
 */
public class HomeServerInfoServlet extends HttpServlet {

    /**
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
     * methods.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/json;charset=UTF-8");
        try (PrintWriter out = response.getWriter()) {
            out.println("{\n"
                    + "    \"platformInfo\": \"Windows 8 v6.2 on amd64; en_US\",\n"
                    + "    \"items\": [\n"
                    + "        {\n"
                    + "            \"name\": \"Main Program\",\n"
                    + "            \"description\": \"The main server program.\",\n"
                    + "            \"state\": \"Running\"\n"
                    + "        },\n"
                    + "        {\n"
                    + "            \"name\": \"Home\",\n"
                    + "            \"description\": \"Provids default HTML pages.\",\n"
                    + "            \"state\": \"Running\"\n"
                    + "        },\n"
                    + "        {\n"
                    + "            \"name\": \"Installer\",\n"
                    + "            \"description\": \"Allows others to clone your server.\",\n"
                    + "            \"state\": \"Running\"\n"
                    + "        }\n"
                    + "    ]\n"
                    + "}");
        }
    }

    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>

}
